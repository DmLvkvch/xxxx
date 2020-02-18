package ru.esphere.school.service;

import ru.esphere.school.data.Member;
import ru.esphere.school.data.MembersGroup;

import java.util.Set;
import java.util.List;
import java.util.stream.Collectors;

public class Finder {
    /**
     * Поиск групп людей старше определенного возраста.
     *
     * @return список имен групп из списка групп старше возраста targetAge
     */

    /**
     * Поиск групп людей старше определенного возраста.
     *
     * @param groups группы
     * @param targetAge возраст для поиска
     * @return список имен групп из списка групп старше возраста targetAge
     */
    public static Set<String> findOldMembers(List<MembersGroup> groups, int targetAge) {
        Set<String> groupsNames = groups.stream().
                map(MembersGroup::getMembers).
                flatMap(Collection::stream).
                filter(member -> member.getAge() > targetAge).
                map(Member::getName).collect(Collectors.toSet());

        return groupsNames;
    }
}
