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
     * @param groups группы
     * @param targetAge возраст для поиска
     * @return список имен групп из списка групп старше возраста targetAge
     */
    public Set<String> findGroupsWithOldMembers(List<MembersGroup> groups, int targetAge){
        Set<String> groupsName = groups.stream().
                filter(group->group.getMembers().stream().allMatch(member -> member.getAge() > targetAge)). //filtering groups
                                                                                    // where each member in group older targetAge
                map(MembersGroup::getGroupName).
                collect(Collectors.toSet());
        return groupsName;
    }

    public Set<String> findOldMembers(List<MembersGroup> groups, int targetAge) {
        Set<String> groupsNames = groups.stream().
                map(MembersGroup::getMembers).
                flatMap(Collection::stream).
                filter(member -> member.getAge() > targetAge).
                map(Member::getName).collect(Collectors.toSet());

        return groupsNames;
    }
}
